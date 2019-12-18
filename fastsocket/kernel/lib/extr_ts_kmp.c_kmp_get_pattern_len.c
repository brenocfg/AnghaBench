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
struct ts_kmp {unsigned int pattern_len; } ;
struct ts_config {int dummy; } ;

/* Variables and functions */
 struct ts_kmp* ts_config_priv (struct ts_config*) ; 

__attribute__((used)) static unsigned int kmp_get_pattern_len(struct ts_config *conf)
{
	struct ts_kmp *kmp = ts_config_priv(conf);
	return kmp->pattern_len;
}