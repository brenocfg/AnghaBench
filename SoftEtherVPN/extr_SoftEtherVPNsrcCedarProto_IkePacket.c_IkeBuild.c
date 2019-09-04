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
typedef  int /*<<< orphan*/  IKE_PACKET ;
typedef  int /*<<< orphan*/  IKE_CRYPTO_PARAM ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * IkeBuildEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

BUF *IkeBuild(IKE_PACKET *p, IKE_CRYPTO_PARAM *cparam)
{
	return IkeBuildEx(p, cparam, false);
}