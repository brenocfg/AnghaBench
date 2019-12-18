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
struct bdx_priv {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdx_hw_reset (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_sw_reset (struct bdx_priv*) ; 

__attribute__((used)) static int bdx_reset(struct bdx_priv *priv)
{
	ENTER;
	RET((priv->pdev->device == 0x3009)
	    ? bdx_hw_reset(priv)
	    : bdx_sw_reset(priv));
}