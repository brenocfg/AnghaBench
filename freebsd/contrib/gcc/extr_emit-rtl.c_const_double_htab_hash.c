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
typedef  int /*<<< orphan*/  rtx ;
typedef  int hashval_t ;

/* Variables and functions */
 int CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 int CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int real_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
const_double_htab_hash (const void *x)
{
  rtx value = (rtx) x;
  hashval_t h;

  if (GET_MODE (value) == VOIDmode)
    h = CONST_DOUBLE_LOW (value) ^ CONST_DOUBLE_HIGH (value);
  else
    {
      h = real_hash (CONST_DOUBLE_REAL_VALUE (value));
      /* MODE is used in the comparison, so it should be in the hash.  */
      h ^= GET_MODE (value);
    }
  return h;
}