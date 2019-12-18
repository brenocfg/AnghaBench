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
typedef  char u8 ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ sqlite3CompareAffinity (int /*<<< orphan*/ *,char) ; 
 scalar_t__ sqlite3ExprAffinity (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 binaryCompareP5(Expr *pExpr1, Expr *pExpr2, int jumpIfNull){
  u8 aff = (char)sqlite3ExprAffinity(pExpr2);
  aff = (u8)sqlite3CompareAffinity(pExpr1, aff) | (u8)jumpIfNull;
  return aff;
}