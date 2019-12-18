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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

char *bin_to_hex_alloc(const uint8_t *data, size_t len)
{
   size_t i;
   char *ret = (char*)malloc(len * 2 + 1);

   if (len && !ret)
      return NULL;

   for (i = 0; i < len; i++)
      snprintf(ret+i * 2, 3, "%02X", data[i]);
   return ret;
}