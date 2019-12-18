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
struct cami2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2CMCR ; 
 int IN32 (struct cami2c*,int /*<<< orphan*/ ) ; 
 int MCR_FSDA ; 

__attribute__((used)) static inline int sh7760_i2c_busy_check(struct cami2c *id)
{
	return (IN32(id, I2CMCR) & MCR_FSDA);
}