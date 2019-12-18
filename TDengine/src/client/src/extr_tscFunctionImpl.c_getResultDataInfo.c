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
typedef  int /*<<< orphan*/  tValuePair ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  STwaInfo ;
typedef  int /*<<< orphan*/  STopBotInfo ;
typedef  int /*<<< orphan*/  SSumInfo ;
typedef  int /*<<< orphan*/  SStddevInfo ;
typedef  int /*<<< orphan*/  SSpreadInfo ;
typedef  int /*<<< orphan*/  SResultInfo ;
typedef  int /*<<< orphan*/  SLastrowInfo ;
typedef  int /*<<< orphan*/  SHistogramInfo ;
typedef  int /*<<< orphan*/  SHistBin ;
typedef  int /*<<< orphan*/  SFirstLastInfo ;
typedef  int /*<<< orphan*/  SAvgInfo ;
typedef  int /*<<< orphan*/  SAPercentileInfo ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG_SIZE ; 
 int MAX_HISTOGRAM_BIN ; 
 int POINTER_BYTES ; 
 int TSDB_AVG_FUNCTION_INTER_BUFFER_SIZE ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BIGINT ; 
 int TSDB_DATA_TYPE_BINARY ; 
 int TSDB_DATA_TYPE_DOUBLE ; 
 scalar_t__ TSDB_DATA_TYPE_TINYINT ; 
 scalar_t__ TSDB_FUNC_APERCT ; 
 scalar_t__ TSDB_FUNC_ARITHM ; 
 scalar_t__ TSDB_FUNC_AVG ; 
 scalar_t__ TSDB_FUNC_BOTTOM ; 
 scalar_t__ TSDB_FUNC_COUNT ; 
 scalar_t__ TSDB_FUNC_DIFF ; 
 scalar_t__ TSDB_FUNC_FIRST ; 
 scalar_t__ TSDB_FUNC_FIRST_DST ; 
 scalar_t__ TSDB_FUNC_INTERP ; 
 scalar_t__ TSDB_FUNC_LAST ; 
 scalar_t__ TSDB_FUNC_LAST_DST ; 
 scalar_t__ TSDB_FUNC_LAST_ROW ; 
 scalar_t__ TSDB_FUNC_LEASTSQR ; 
 scalar_t__ TSDB_FUNC_MAX ; 
 scalar_t__ TSDB_FUNC_MIN ; 
 scalar_t__ TSDB_FUNC_PERCT ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_SPREAD ; 
 scalar_t__ TSDB_FUNC_STDDEV ; 
 scalar_t__ TSDB_FUNC_SUM ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TAG_DUMMY ; 
 scalar_t__ TSDB_FUNC_TOP ; 
 scalar_t__ TSDB_FUNC_TS ; 
 scalar_t__ TSDB_FUNC_TS_COMP ; 
 scalar_t__ TSDB_FUNC_TS_DUMMY ; 
 scalar_t__ TSDB_FUNC_TWA ; 
 int /*<<< orphan*/  isValidDataType (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pError (char*,scalar_t__,scalar_t__) ; 

int32_t getResultDataInfo(int32_t dataType, int32_t dataBytes, int32_t functionId, int32_t param, int16_t *type,
                          int16_t *bytes, int16_t *intermediateResBytes, int16_t extLength, bool isSuperTable) {
  if (!isValidDataType(dataType, dataBytes)) {
    pError("Illegal data type %d or data type length %d", dataType, dataBytes);
    return TSDB_CODE_INVALID_SQL;
  }

  if (functionId == TSDB_FUNC_TS || functionId == TSDB_FUNC_TS_DUMMY || functionId == TSDB_FUNC_TAG_DUMMY ||
      functionId == TSDB_FUNC_DIFF || functionId == TSDB_FUNC_PRJ || functionId == TSDB_FUNC_TAGPRJ ||
      functionId == TSDB_FUNC_TAG || functionId == TSDB_FUNC_INTERP) {
    *type = (int16_t)dataType;
    *bytes = (int16_t)dataBytes;
    *intermediateResBytes = *bytes + sizeof(SResultInfo);
    return TSDB_CODE_SUCCESS;
  }

  if (functionId == TSDB_FUNC_COUNT) {
    *type = TSDB_DATA_TYPE_BIGINT;
    *bytes = sizeof(int64_t);
    *intermediateResBytes = *bytes;
    return TSDB_CODE_SUCCESS;
  }

  if (functionId == TSDB_FUNC_ARITHM) {
    *type = TSDB_DATA_TYPE_DOUBLE;
    *bytes = sizeof(double);
    *intermediateResBytes = *bytes;
    return TSDB_CODE_SUCCESS;
  }

  if (functionId == TSDB_FUNC_TS_COMP) {
    *type = TSDB_DATA_TYPE_BINARY;
    *bytes = sizeof(int32_t);  // this results is compressed ts data
    *intermediateResBytes = POINTER_BYTES;
    return TSDB_CODE_SUCCESS;
  }

  if (isSuperTable) {
    if (functionId == TSDB_FUNC_MIN || functionId == TSDB_FUNC_MAX) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = dataBytes + DATA_SET_FLAG_SIZE;
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_SUM) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = sizeof(SSumInfo);
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_AVG) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = sizeof(SAvgInfo);
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_TOP || functionId == TSDB_FUNC_BOTTOM) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = sizeof(STopBotInfo) + (sizeof(tValuePair) + POINTER_BYTES + extLength) * param;
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_SPREAD) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = sizeof(SSpreadInfo);
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_APERCT) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = sizeof(SHistBin) * (MAX_HISTOGRAM_BIN + 1) + sizeof(SHistogramInfo) + sizeof(SAPercentileInfo);
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_LAST_ROW) {
      *type = TSDB_DATA_TYPE_BINARY;
      *bytes = sizeof(SLastrowInfo) + dataBytes;
      *intermediateResBytes = *bytes;

      return TSDB_CODE_SUCCESS;
    } else if (functionId == TSDB_FUNC_TWA) {
      *type = TSDB_DATA_TYPE_DOUBLE;
      *bytes = sizeof(STwaInfo);
      *intermediateResBytes = sizeof(STwaInfo);
      return TSDB_CODE_SUCCESS;
    }
  }

  if (functionId == TSDB_FUNC_SUM) {
    if (dataType >= TSDB_DATA_TYPE_TINYINT && dataType <= TSDB_DATA_TYPE_BIGINT) {
      *type = TSDB_DATA_TYPE_BIGINT;
    } else {
      *type = TSDB_DATA_TYPE_DOUBLE;
    }

    *bytes = sizeof(int64_t);
    *intermediateResBytes = sizeof(SSumInfo);
    return TSDB_CODE_SUCCESS;
  } else if (functionId == TSDB_FUNC_APERCT) {
    *type = TSDB_DATA_TYPE_DOUBLE;
    *bytes = sizeof(double);
    *intermediateResBytes =
        sizeof(SAPercentileInfo) + sizeof(SHistogramInfo) + sizeof(SHistBin) * (MAX_HISTOGRAM_BIN + 1);
    return TSDB_CODE_SUCCESS;
  } else if (functionId == TSDB_FUNC_TWA) {
    *type = TSDB_DATA_TYPE_DOUBLE;
    *bytes = sizeof(double);
    *intermediateResBytes = sizeof(STwaInfo);
    return TSDB_CODE_SUCCESS;
  }

  if (functionId == TSDB_FUNC_AVG) {
    *type = TSDB_DATA_TYPE_DOUBLE;
    *bytes = sizeof(double);
    *intermediateResBytes = sizeof(SAvgInfo);
  } else if (functionId == TSDB_FUNC_STDDEV) {
    *type = TSDB_DATA_TYPE_DOUBLE;
    *bytes = sizeof(double);
    *intermediateResBytes = sizeof(SStddevInfo);
  } else if (functionId == TSDB_FUNC_MIN || functionId == TSDB_FUNC_MAX) {
    *type = (int16_t)dataType;
    *bytes = (int16_t)dataBytes;
    *intermediateResBytes = dataBytes + DATA_SET_FLAG_SIZE;
  } else if (functionId == TSDB_FUNC_FIRST || functionId == TSDB_FUNC_LAST) {
    *type = (int16_t)dataType;
    *bytes = (int16_t)dataBytes;
    *intermediateResBytes = dataBytes + sizeof(SResultInfo);
  } else if (functionId == TSDB_FUNC_SPREAD) {
    *type = (int16_t)TSDB_DATA_TYPE_DOUBLE;
    *bytes = sizeof(double);
    *intermediateResBytes = sizeof(SSpreadInfo);
  } else if (functionId == TSDB_FUNC_PERCT) {
    *type = (int16_t)TSDB_DATA_TYPE_DOUBLE;
    *bytes = (int16_t)sizeof(double);
    //*intermediateResBytes = POINTER_BYTES;
    *intermediateResBytes = (int16_t)sizeof(double);
  } else if (functionId == TSDB_FUNC_LEASTSQR) {
    *type = TSDB_DATA_TYPE_BINARY;
    *bytes = TSDB_AVG_FUNCTION_INTER_BUFFER_SIZE;  // string
    *intermediateResBytes = *bytes + sizeof(SResultInfo);
  } else if (functionId == TSDB_FUNC_FIRST_DST || functionId == TSDB_FUNC_LAST_DST) {
    *type = TSDB_DATA_TYPE_BINARY;
    *bytes = dataBytes + sizeof(SFirstLastInfo);
    *intermediateResBytes = *bytes;
  } else if (functionId == TSDB_FUNC_TOP || functionId == TSDB_FUNC_BOTTOM) {
    *type = (int16_t)dataType;
    *bytes = (int16_t)dataBytes;

    size_t size = sizeof(STopBotInfo) + (sizeof(tValuePair) + POINTER_BYTES + extLength) * param;

    // the output column may be larger than sizeof(STopBotInfo)
    *intermediateResBytes = size;
  } else if (functionId == TSDB_FUNC_LAST_ROW) {
    *type = (int16_t)dataType;
    *bytes = (int16_t)dataBytes;
    *intermediateResBytes = dataBytes + sizeof(SLastrowInfo);
  } else {
    return TSDB_CODE_INVALID_SQL;
  }

  return TSDB_CODE_SUCCESS;
}