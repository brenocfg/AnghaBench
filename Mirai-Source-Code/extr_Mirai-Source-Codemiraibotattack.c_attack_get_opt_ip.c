#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct attack_option {int dummy; } ;

/* Variables and functions */
 char* attack_get_opt_str (int /*<<< orphan*/ ,struct attack_option*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 

uint32_t attack_get_opt_ip(uint8_t opts_len, struct attack_option *opts, uint8_t opt, uint32_t def)
{
    char *val = attack_get_opt_str(opts_len, opts, opt, NULL);

    if (val == NULL)
        return def;
    else
        return inet_addr(val);
}