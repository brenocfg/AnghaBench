#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* tree1d; } ;
typedef  TYPE_1__ HuffmanTree ;

/* Variables and functions */

__attribute__((used)) static unsigned HuffmanTree_getCode(const HuffmanTree* tree, unsigned index)
{
  return tree->tree1d[index];
}