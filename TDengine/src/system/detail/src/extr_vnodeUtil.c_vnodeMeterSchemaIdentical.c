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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  SColumn ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDNUMOFCOLS (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

bool vnodeMeterSchemaIdentical(SColumn* pSchema1, int32_t numOfCols1, SColumn* pSchema2, int32_t numOfCols2) {
  if (!VALIDNUMOFCOLS(numOfCols1) || !VALIDNUMOFCOLS(numOfCols2) || numOfCols1 != numOfCols2) {
    return false;
  }

  return memcmp((char*)pSchema1, (char*)pSchema2, sizeof(SColumn) * numOfCols1) == 0;
}