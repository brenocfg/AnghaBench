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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ n; scalar_t__ type; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 scalar_t__ TK_ID ; 
 scalar_t__ TK_STRING ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ strdequote (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtrim (int /*<<< orphan*/ ) ; 
 scalar_t__ tSQLGetToken (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ tscValidateName (TYPE_1__*) ; 

__attribute__((used)) static int32_t validateQuoteToken(SSQLToken* pToken) {
  pToken->n = strdequote(pToken->z);
  strtrim(pToken->z);
  pToken->n = (uint32_t)strlen(pToken->z);

  int32_t k = tSQLGetToken(pToken->z, &pToken->type);

  if (pToken->type == TK_STRING) {
    return tscValidateName(pToken);
  }

  if (k != pToken->n || pToken->type != TK_ID) {
    return TSDB_CODE_INVALID_SQL;
  }
  return TSDB_CODE_SUCCESS;
}