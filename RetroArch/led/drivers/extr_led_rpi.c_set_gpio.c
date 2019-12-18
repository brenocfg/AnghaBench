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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int set_gpio(int gpio, int value)
{
   FILE *fp;
   char buf[256];
   snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
   fp = fopen(buf, "w");

   if(!fp)
   {
      RARCH_WARN("[LED]: failed to set GPIO %d\n", gpio);
      return -1;
   }

   fprintf(fp, "%d\n", value ? 1 : 0);
   fclose(fp);
   return 1;
}