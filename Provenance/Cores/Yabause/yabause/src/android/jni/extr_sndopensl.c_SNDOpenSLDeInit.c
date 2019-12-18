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
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int MAX_BUFFER_CNT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** stereodata16 ; 

__attribute__((used)) static void SNDOpenSLDeInit(void)
{
   int i;
   JNIEnv * env;

   for( i=0; i< MAX_BUFFER_CNT; i++ )
   {
      free(stereodata16[i]);
      stereodata16[i] = NULL;
   }

}