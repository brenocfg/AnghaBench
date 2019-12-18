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
 int ROUNDED_DIV (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static inline void vect_division(int *res, int *vect, int div, int dim)
{
    int i;
    if (div > 1)
        for (i=0; i<dim; i++)
            res[i] = ROUNDED_DIV(vect[i],div);
    else if (res != vect)
        memcpy(res, vect, dim*sizeof(int));

}