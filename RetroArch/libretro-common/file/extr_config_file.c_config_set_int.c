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
typedef  int /*<<< orphan*/  config_file_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  config_set_string (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void config_set_int(config_file_t *conf, const char *key, int val)
{
   char buf[128];

   buf[0] = '\0';
   snprintf(buf, sizeof(buf), "%d", val);
   config_set_string(conf, key, buf);
}