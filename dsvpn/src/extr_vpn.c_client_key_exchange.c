#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int is_server; int /*<<< orphan*/ * uc_st; int /*<<< orphan*/  client_fd; int /*<<< orphan*/ * uc_kx_st; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  endian_swap64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int safe_read (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int safe_write (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uc_hash (int*,int*,int*,int) ; 
 int /*<<< orphan*/  uc_randombytes_buf (int*,int) ; 
 int /*<<< orphan*/  uc_state_init (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int client_key_exchange(Context *context)
{
    uint32_t st[12];
    uint8_t  pkt1[32 + 8 + 32], pkt2[32 + 32];
    uint8_t  h[32];
    uint8_t  k[32];
    uint8_t  iv[16] = { 0 };
    uint64_t now;

    memcpy(st, context->uc_kx_st, sizeof st);
    uc_randombytes_buf(pkt1, 32);
    now = endian_swap64(time(NULL));
    memcpy(pkt1 + 32, &now, 8);
    uc_hash(st, pkt1 + 32 + 8, pkt1, 32 + 8);
    if (safe_write(context->client_fd, pkt1, sizeof pkt1, TIMEOUT) != sizeof pkt1) {
        return -1;
    }
    errno = EACCES;
    if (safe_read(context->client_fd, pkt2, sizeof pkt2, TIMEOUT) != sizeof pkt2) {
        return -1;
    }
    uc_hash(st, h, pkt2, 32);
    if (memcmp(h, pkt2 + 32, 32) != 0) {
        return -1;
    }
    uc_hash(st, k, NULL, 0);
    iv[0] = context->is_server;
    uc_state_init(context->uc_st[0], k, iv);
    iv[0] ^= 1;
    uc_state_init(context->uc_st[1], k, iv);

    return 0;
}