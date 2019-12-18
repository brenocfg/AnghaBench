#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {scalar_t__ uid; scalar_t__ sversion; int numOfColumns; scalar_t__ numOfTags; } ;
struct TYPE_9__ {scalar_t__ bytes; } ;
typedef  TYPE_1__ SSchema ;
typedef  TYPE_2__ SMeterMeta ;

/* Variables and functions */
 scalar_t__ memcmp (TYPE_2__*,TYPE_2__*,size_t) ; 
 TYPE_1__* tsGetColumnSchema (TYPE_2__*,scalar_t__) ; 

bool tsMeterMetaIdentical(SMeterMeta* p1, SMeterMeta* p2) {
  if (p1 == NULL || p2 == NULL || p1->uid != p2->uid || p1->sversion != p2->sversion) {
    return false;
  }

  if (p1 == p2) {
    return true;
  }

  size_t size = sizeof(SMeterMeta) + p1->numOfColumns * sizeof(SSchema);

  for (int32_t i = 0; i < p1->numOfTags; ++i) {
    SSchema* pColSchema = tsGetColumnSchema(p1, i + p1->numOfColumns);
    size += pColSchema->bytes;
  }

  return memcmp(p1, p2, size) == 0;
}