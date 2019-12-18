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
struct prism2_wep_data {int key_idx; int key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static char * prism2_wep_print_stats(char *p, void *priv)
{
	struct prism2_wep_data *wep = priv;
	p += sprintf(p, "key[%d] alg=WEP len=%d\n",
		     wep->key_idx, wep->key_len);
	return p;
}