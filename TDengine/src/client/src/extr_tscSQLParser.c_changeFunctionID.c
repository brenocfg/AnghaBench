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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  TK_APERCENTILE 145 
#define  TK_AVG 144 
#define  TK_BOTTOM 143 
#define  TK_COUNT 142 
#define  TK_DIFF 141 
#define  TK_FIRST 140 
#define  TK_INTERP 139 
#define  TK_LAST 138 
#define  TK_LAST_ROW 137 
#define  TK_LEASTSQUARES 136 
#define  TK_MAX 135 
#define  TK_MIN 134 
#define  TK_PERCENTILE 133 
#define  TK_SPREAD 132 
#define  TK_STDDEV 131 
#define  TK_SUM 130 
#define  TK_TOP 129 
#define  TK_TWA 128 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_FUNC_APERCT ; 
 int /*<<< orphan*/  TSDB_FUNC_AVG ; 
 int /*<<< orphan*/  TSDB_FUNC_BOTTOM ; 
 int /*<<< orphan*/  TSDB_FUNC_COUNT ; 
 int /*<<< orphan*/  TSDB_FUNC_DIFF ; 
 int /*<<< orphan*/  TSDB_FUNC_FIRST ; 
 int /*<<< orphan*/  TSDB_FUNC_INTERP ; 
 int /*<<< orphan*/  TSDB_FUNC_LAST ; 
 int /*<<< orphan*/  TSDB_FUNC_LAST_ROW ; 
 int /*<<< orphan*/  TSDB_FUNC_LEASTSQR ; 
 int /*<<< orphan*/  TSDB_FUNC_MAX ; 
 int /*<<< orphan*/  TSDB_FUNC_MIN ; 
 int /*<<< orphan*/  TSDB_FUNC_PERCT ; 
 int /*<<< orphan*/  TSDB_FUNC_SPREAD ; 
 int /*<<< orphan*/  TSDB_FUNC_STDDEV ; 
 int /*<<< orphan*/  TSDB_FUNC_SUM ; 
 int /*<<< orphan*/  TSDB_FUNC_TOP ; 
 int /*<<< orphan*/  TSDB_FUNC_TWA ; 

int32_t changeFunctionID(int32_t optr, int16_t* functionId) {
  switch (optr) {
    case TK_COUNT:
      *functionId = TSDB_FUNC_COUNT;
      break;
    case TK_SUM:
      *functionId = TSDB_FUNC_SUM;
      break;
    case TK_AVG:
      *functionId = TSDB_FUNC_AVG;
      break;
    case TK_MIN:
      *functionId = TSDB_FUNC_MIN;
      break;
    case TK_MAX:
      *functionId = TSDB_FUNC_MAX;
      break;
    case TK_STDDEV:
      *functionId = TSDB_FUNC_STDDEV;
      break;
    case TK_PERCENTILE:
      *functionId = TSDB_FUNC_PERCT;
      break;
    case TK_APERCENTILE:
      *functionId = TSDB_FUNC_APERCT;
      break;
    case TK_FIRST:
      *functionId = TSDB_FUNC_FIRST;
      break;
    case TK_LAST:
      *functionId = TSDB_FUNC_LAST;
      break;
    case TK_LEASTSQUARES:
      *functionId = TSDB_FUNC_LEASTSQR;
      break;
    case TK_TOP:
      *functionId = TSDB_FUNC_TOP;
      break;
    case TK_BOTTOM:
      *functionId = TSDB_FUNC_BOTTOM;
      break;
    case TK_DIFF:
      *functionId = TSDB_FUNC_DIFF;
      break;
    case TK_SPREAD:
      *functionId = TSDB_FUNC_SPREAD;
      break;
    case TK_TWA:
      *functionId = TSDB_FUNC_TWA;
      break;
    case TK_INTERP:
      *functionId = TSDB_FUNC_INTERP;
      break;
    case TK_LAST_ROW:
      *functionId = TSDB_FUNC_LAST_ROW;
      break;
    default:
      return -1;
  }

  return TSDB_CODE_SUCCESS;
}