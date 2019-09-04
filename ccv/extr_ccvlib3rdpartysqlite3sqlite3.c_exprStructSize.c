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
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Reduced ; 
 int /*<<< orphan*/  EP_TokenOnly ; 
 int EXPR_FULLSIZE ; 
 int EXPR_REDUCEDSIZE ; 
 int EXPR_TOKENONLYSIZE ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exprStructSize(Expr *p){
  if( ExprHasProperty(p, EP_TokenOnly) ) return EXPR_TOKENONLYSIZE;
  if( ExprHasProperty(p, EP_Reduced) ) return EXPR_REDUCEDSIZE;
  return EXPR_FULLSIZE;
}