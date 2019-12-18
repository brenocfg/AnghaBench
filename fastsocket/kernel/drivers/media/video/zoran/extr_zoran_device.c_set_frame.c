#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * gpio; } ;
struct zoran {TYPE_1__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO (struct zoran*,int /*<<< orphan*/ ,int) ; 
 size_t ZR_GPIO_JPEG_FRAME ; 

__attribute__((used)) static inline void
set_frame (struct zoran *zr,
	   int           val)
{
	GPIO(zr, zr->card.gpio[ZR_GPIO_JPEG_FRAME], val);
}