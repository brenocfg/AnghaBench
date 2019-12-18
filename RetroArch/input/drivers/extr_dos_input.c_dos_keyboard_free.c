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

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int MAX_KEYS ; 
 scalar_t__** dos_key_state ; 

__attribute__((used)) static void dos_keyboard_free(void)
{
   unsigned i, j;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
      for (j = 0; j < MAX_KEYS; j++)
         dos_key_state[i][j] = 0;
}