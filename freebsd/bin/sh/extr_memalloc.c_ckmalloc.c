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
typedef  int /*<<< orphan*/ * pointer ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

pointer
ckmalloc(size_t nbytes)
{
	pointer p;

	INTOFF;
	p = malloc(nbytes);
	INTON;
	if (p == NULL)
		error("Out of space");
	return p;
}