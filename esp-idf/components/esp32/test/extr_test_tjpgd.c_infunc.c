#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {scalar_t__ device; } ;
struct TYPE_4__ {int inPos; int inData; } ;
typedef  TYPE_1__ JpegDev ;
typedef  TYPE_2__ JDEC ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static UINT infunc(JDEC *decoder, BYTE *buf, UINT len)
{
    JpegDev *jd = (JpegDev *)decoder->device;
    printf("Reading %d bytes from pos %d\n", len, jd->inPos);
    if (buf != NULL) {
        memcpy(buf, jd->inData + jd->inPos, len);
    }
    jd->inPos += len;
    return len;
}