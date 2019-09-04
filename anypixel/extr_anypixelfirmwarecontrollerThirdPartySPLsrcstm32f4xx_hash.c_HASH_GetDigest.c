#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * HR; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Data; } ;
typedef  TYPE_1__ HASH_MsgDigest ;

/* Variables and functions */
 TYPE_3__* HASH ; 

void HASH_GetDigest(HASH_MsgDigest* HASH_MessageDigest)
{
  /* Get the data field */
  HASH_MessageDigest->Data[0] = HASH->HR[0];
  HASH_MessageDigest->Data[1] = HASH->HR[1];
  HASH_MessageDigest->Data[2] = HASH->HR[2];
  HASH_MessageDigest->Data[3] = HASH->HR[3];
  HASH_MessageDigest->Data[4] = HASH->HR[4];
}