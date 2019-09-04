#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ next; } ;
struct TYPE_6__ {int dcode_insert_length; int length; TYPE_1__ u; } ;
typedef  TYPE_2__ ZopfliNode ;

/* Variables and functions */
 scalar_t__ BROTLI_UINT32_MAX ; 
 size_t ZopfliNodeCommandLength (TYPE_2__*) ; 

__attribute__((used)) static size_t ComputeShortestPathFromNodes(size_t num_bytes,
    ZopfliNode* nodes) {
  size_t index = num_bytes;
  size_t num_commands = 0;
  while ((nodes[index].dcode_insert_length & 0x7FFFFFF) == 0 &&
      nodes[index].length == 1) --index;
  nodes[index].u.next = BROTLI_UINT32_MAX;
  while (index != 0) {
    size_t len = ZopfliNodeCommandLength(&nodes[index]);
    index -= len;
    nodes[index].u.next = (uint32_t)len;
    num_commands++;
  }
  return num_commands;
}