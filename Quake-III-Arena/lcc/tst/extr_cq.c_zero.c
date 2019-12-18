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
 int k ; 

zero(){                 /* Returns a value of zero, possibly */
   static k;            /* with side effects, as it's called */
   int rc;              /* alternately with svtest, above,   */
   k = 2;               /* and has the same internal storage */
   rc = 0;              /* requirements.                     */
   return rc;
}