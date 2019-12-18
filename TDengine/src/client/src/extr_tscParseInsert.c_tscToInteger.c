#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 scalar_t__ TK_BIN ; 
 scalar_t__ TK_HEX ; 
 scalar_t__ TK_ILLEGAL ; 
 scalar_t__ TK_OCT ; 
 scalar_t__ isValidNumber (TYPE_1__*) ; 
 int /*<<< orphan*/  strtoll (int /*<<< orphan*/ ,char**,scalar_t__) ; 

__attribute__((used)) static int32_t tscToInteger(SSQLToken *pToken, int64_t *value, char **endPtr) {
  int32_t numType = isValidNumber(pToken);
  if (TK_ILLEGAL == numType) {
    return numType;
  }

  int32_t radix = 10;
  if (numType == TK_HEX) {
    radix = 16;
  } else if (numType == TK_OCT) {
    radix = 8;
  } else if (numType == TK_BIN) {
    radix = 2;
  }

  *value = strtoll(pToken->z, endPtr, radix);

  return numType;
}