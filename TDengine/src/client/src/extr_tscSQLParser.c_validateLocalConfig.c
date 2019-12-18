#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nTokens; TYPE_2__* a; } ;
typedef  TYPE_1__ tDCLSQL ;
typedef  int int32_t ;
struct TYPE_8__ {char* member_0; int member_1; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ SSQLToken ;
typedef  TYPE_3__ SDNodeDynConfOption ;

/* Variables and functions */
 int TSDB_CODE_INVALID_SQL ; 
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int tListLen (TYPE_3__*) ; 

int32_t validateLocalConfig(tDCLSQL* pOptions) {
  if (pOptions->nTokens < 1 || pOptions->nTokens > 2) {
    return TSDB_CODE_INVALID_SQL;
  }

  SDNodeDynConfOption LOCAL_DYNAMIC_CFG_OPTIONS[6] = {{"resetLog", 8},    {"rpcDebugFlag", 12}, {"tmrDebugFlag", 12},
                                                      {"cDebugFlag", 10}, {"uDebugFlag", 10},   {"debugFlag", 9}};

  SSQLToken* pOptionToken = &pOptions->a[0];

  if (pOptions->nTokens == 1) {
    // reset log does not need value
    for (int32_t i = 0; i < 1; ++i) {
      SDNodeDynConfOption* pOption = &LOCAL_DYNAMIC_CFG_OPTIONS[i];
      if ((strncasecmp(pOption->name, pOptionToken->z, pOptionToken->n) == 0) && (pOption->len == pOptionToken->n)) {
        return TSDB_CODE_SUCCESS;
      }
    }
  } else {
    SSQLToken* pValToken = &pOptions->a[1];

    int32_t val = strtol(pValToken->z, NULL, 10);
    if (val < 131 || val > 199) {
      // options value is out of valid range
      return TSDB_CODE_INVALID_SQL;
    }

    for (int32_t i = 1; i < tListLen(LOCAL_DYNAMIC_CFG_OPTIONS); ++i) {
      SDNodeDynConfOption* pOption = &LOCAL_DYNAMIC_CFG_OPTIONS[i];
      if ((strncasecmp(pOption->name, pOptionToken->z, pOptionToken->n) == 0) && (pOption->len == pOptionToken->n)) {
        // options is valid
        return TSDB_CODE_SUCCESS;
      }
    }
  }
  return TSDB_CODE_INVALID_SQL;
}