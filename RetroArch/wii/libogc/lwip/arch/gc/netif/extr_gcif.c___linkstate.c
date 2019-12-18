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
typedef  int u8 ;
struct bba_priv {int linkstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBA_NWAYS ; 
 int BBA_NWAYS_LS10 ; 
 int BBA_NWAYS_LS100 ; 
 int bba_in8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ u8 __linkstate(struct bba_priv *priv)
{
	u8 nways = 0;

	nways = bba_in8(BBA_NWAYS);
	priv->linkstate = nways;
	if(nways&BBA_NWAYS_LS10 || nways&BBA_NWAYS_LS100) return nways;
	return 0;
}