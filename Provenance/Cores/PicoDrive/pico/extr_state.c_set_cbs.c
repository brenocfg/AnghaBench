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
typedef  int /*<<< orphan*/  areaseek ;
typedef  int /*<<< orphan*/  arearw ;
typedef  int /*<<< orphan*/  areaeof ;
typedef  int /*<<< orphan*/  areaclose ;

/* Variables and functions */
 int /*<<< orphan*/ * areaClose ; 
 int /*<<< orphan*/ * areaEof ; 
 int /*<<< orphan*/ * areaRead ; 
 int /*<<< orphan*/ * areaSeek ; 
 int /*<<< orphan*/ * areaWrite ; 
 scalar_t__ fclose ; 
 scalar_t__ feof ; 
 scalar_t__ fread ; 
 scalar_t__ fseek ; 
 scalar_t__ fwrite ; 
 int /*<<< orphan*/ * gzRead2 ; 
 int /*<<< orphan*/ * gzWrite2 ; 
 scalar_t__ gzclose ; 
 scalar_t__ gzeof ; 
 scalar_t__ gzseek ; 

__attribute__((used)) static void set_cbs(int gz)
{
  if (gz) {
    areaRead  = gzRead2;
    areaWrite = gzWrite2;
    areaEof   = (areaeof *) gzeof;
    areaSeek  = (areaseek *) gzseek;
    areaClose = (areaclose *) gzclose;
  } else {
    areaRead  = (arearw *) fread;
    areaWrite = (arearw *) fwrite;
    areaEof   = (areaeof *) feof;
    areaSeek  = (areaseek *) fseek;
    areaClose = (areaclose *) fclose;
  }
}