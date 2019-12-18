#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int avail_in; scalar_t__ total_out; scalar_t__ total_in; int avail_out; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * next_out; scalar_t__ opaque; scalar_t__ zfree; scalar_t__ zalloc; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ z_stream ;
typedef  scalar_t__ voidpf ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ free_func ;
typedef  int /*<<< orphan*/  dummyHead ;
typedef  scalar_t__ alloc_func ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int Z_DATA_ERROR ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit2 (TYPE_1__*,int) ; 

int httpGzipDeCompress(char *srcData, int32_t nSrcData, char *destData, int32_t *nDestData) {
  int err = 0;
  z_stream gzipStream = {0};

  static char dummyHead[2] = {
          0x8 + 0x7 * 0x10,
          (((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
  };

  gzipStream.zalloc = (alloc_func) 0;
  gzipStream.zfree = (free_func) 0;
  gzipStream.opaque = (voidpf) 0;
  gzipStream.next_in = (Bytef *) srcData;
  gzipStream.avail_in = 0;
  gzipStream.next_out = (Bytef *) destData;
  if (inflateInit2(&gzipStream, 47) != Z_OK) {
    return -1;
  }

  while (gzipStream.total_out < *nDestData && gzipStream.total_in < nSrcData) {
    gzipStream.avail_in = gzipStream.avail_out = nSrcData;  //1
    if ((err = inflate(&gzipStream, Z_NO_FLUSH)) == Z_STREAM_END) {
      break;
    }

    if (err != Z_OK) {
      if (err == Z_DATA_ERROR) {
        gzipStream.next_in = (Bytef *) dummyHead;
        gzipStream.avail_in = sizeof(dummyHead);
        if ((err = inflate(&gzipStream, Z_NO_FLUSH)) != Z_OK) {
          return -2;
        }
      } else return -3;
    }
  }

  if (inflateEnd(&gzipStream) != Z_OK) {
    return -4;
  }
  *nDestData = gzipStream.total_out;

  return 0;
}