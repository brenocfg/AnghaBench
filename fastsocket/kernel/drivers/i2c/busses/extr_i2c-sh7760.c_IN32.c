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
struct cami2c {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned long ctrl_inl (unsigned long) ; 

__attribute__((used)) static inline unsigned long IN32(struct cami2c *cam, int reg)
{
	return ctrl_inl((unsigned long)cam->iobase + reg);
}