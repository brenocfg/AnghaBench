#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char* data; } ;
typedef  TYPE_3__ tFilePage ;
typedef  size_t int32_t ;
struct TYPE_21__ {TYPE_2__* resColModel; } ;
struct TYPE_15__ {size_t numOfExprs; } ;
struct TYPE_20__ {TYPE_1__ exprsInfo; } ;
struct TYPE_19__ {int numOfRows; char* data; } ;
struct TYPE_18__ {int bytes; } ;
struct TYPE_16__ {size_t* colOffset; } ;
typedef  TYPE_4__ TAOS_FIELD ;
typedef  TYPE_5__ SSqlRes ;
typedef  TYPE_6__ SSqlCmd ;
typedef  TYPE_7__ SLocalReducer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 TYPE_4__* tscFieldInfoGetField (TYPE_6__*,size_t) ; 
 size_t tscFieldInfoGetOffset (TYPE_6__*,size_t) ; 

__attribute__((used)) static void reversedCopyFromInterpolationToDstBuf(SSqlCmd *pCmd, SSqlRes *pRes, tFilePage **pResPages,
                                                  SLocalReducer *pLocalReducer) {
  for (int32_t i = 0; i < pCmd->exprsInfo.numOfExprs; ++i) {
    TAOS_FIELD *pField = tscFieldInfoGetField(pCmd, i);

    int32_t offset = tscFieldInfoGetOffset(pCmd, i);
    assert(offset == pLocalReducer->resColModel->colOffset[i]);

    char *src = pResPages[i]->data + (pRes->numOfRows - 1) * pField->bytes;
    char *dst = pRes->data + pRes->numOfRows * offset;

    for (int32_t j = 0; j < pRes->numOfRows; ++j) {
      memcpy(dst, src, (size_t)pField->bytes);
      dst += pField->bytes;
      src -= pField->bytes;
    }
  }
}