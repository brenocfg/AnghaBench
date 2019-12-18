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
typedef  scalar_t__ voidpf ;
typedef  int /*<<< orphan*/  uInt ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  calloc (unsigned int,unsigned int) ; 
 scalar_t__ malloc (unsigned int) ; 

voidpf
zcalloc(voidpf opaque, unsigned items, unsigned size)
{
    if (opaque) items += size - size; /* make compiler happy */
    if (sizeof(uInt) > 2) {
        /*
            to prevent use of uninitialized memory, malloc and bzero
        */
        voidpf  p = malloc(items * size);
        bzero(p, items * size); 
        return p;
    } else
        return (voidpf)calloc(items, size);
}