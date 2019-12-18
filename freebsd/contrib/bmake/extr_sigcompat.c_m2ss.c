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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  MASK_T ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
m2ss(sigset_t *ss, MASK_T *m)
{
	if (sizeof(sigset_t) > sizeof(MASK_T))
		memset((char *) ss, 0, sizeof(sigset_t));

	memcpy((char *) ss, (char *) m, sizeof(MASK_T));
}