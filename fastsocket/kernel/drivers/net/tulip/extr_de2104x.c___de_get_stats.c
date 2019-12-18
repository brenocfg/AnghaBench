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
typedef  int /*<<< orphan*/  u32 ;
struct de_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RxMissed ; 
 int /*<<< orphan*/  de_rx_missed (struct de_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __de_get_stats(struct de_private *de)
{
	u32 tmp = dr32(RxMissed); /* self-clearing */

	de_rx_missed(de, tmp);
}