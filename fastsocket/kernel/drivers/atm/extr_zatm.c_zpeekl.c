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
typedef  int u32 ;
struct zatm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CER ; 
 int /*<<< orphan*/  CMR ; 
 int uPD98401_IA_BALL ; 
 int uPD98401_IA_RW ; 
 int uPD98401_IA_TGT_CM ; 
 int uPD98401_IA_TGT_SHIFT ; 
 int uPD98401_IND_ACC ; 
 int zin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zout (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwait ; 

__attribute__((used)) static u32 zpeekl(struct zatm_dev *zatm_dev,u32 addr)
{
	zwait;
	zout(uPD98401_IND_ACC | uPD98401_IA_BALL | uPD98401_IA_RW |
	  (uPD98401_IA_TGT_CM << uPD98401_IA_TGT_SHIFT) | addr,CMR);
	zwait;
	return zin(CER);
}