#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uLong ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {scalar_t__ avail_in; scalar_t__ total_out; scalar_t__ avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
struct TYPE_5__ {TYPE_3__ gzipStream; } ;
typedef  TYPE_1__ HttpContext ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_FULL_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int deflateEnd (TYPE_3__*) ; 

int httpGzipCompress(HttpContext *pContext, char *srcData, int32_t nSrcData, char *destData, int32_t *nDestData, bool isTheLast) {
  int err = 0;
  pContext->gzipStream.next_in = (Bytef *) srcData;
  pContext->gzipStream.avail_in = (uLong) nSrcData;
  pContext->gzipStream.next_out = (Bytef *) destData;
  pContext->gzipStream.avail_out = (uLong) (*nDestData);

  while (pContext->gzipStream.avail_in != 0 && pContext->gzipStream.total_out < (uLong) (*nDestData)) {
    if (deflate(&pContext->gzipStream, Z_FULL_FLUSH) != Z_OK) {
      return -1;
    }
  }

  if (pContext->gzipStream.avail_in != 0) {
    return pContext->gzipStream.avail_in;
  }

  if (isTheLast) {
    for (;;) {
      if ((err = deflate(&pContext->gzipStream, Z_FINISH)) == Z_STREAM_END) {
        break;
      }
      if (err != Z_OK) {
        return -2;
      }
    }

    if (deflateEnd(&pContext->gzipStream) != Z_OK) {
      return -3;
    }
  }

  *nDestData = (int32_t) (pContext->gzipStream.total_out);
  return 0;
}