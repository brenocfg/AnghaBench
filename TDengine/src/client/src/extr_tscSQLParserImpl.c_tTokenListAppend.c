#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nTokens; int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ tDCLSQL ;
typedef  int /*<<< orphan*/  SSQLToken ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  tTokenListBuyMoreSpace (TYPE_1__*) ; 

tDCLSQL *tTokenListAppend(tDCLSQL *pTokenList, SSQLToken *pToken) {
  if (pToken == NULL) return NULL;

  if (pTokenList == NULL) pTokenList = calloc(1, sizeof(tDCLSQL));

  tTokenListBuyMoreSpace(pTokenList);
  pTokenList->a[pTokenList->nTokens++] = *pToken;

  return pTokenList;
}