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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_5__ {int type; int size; int* symbols; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int update_model2_to_3(PixelModel3 *m, uint32_t val)
{
    PixelModel3 n = {0};
    uint32_t size;

    n.type = 3;
    n.size = m->size + 1;

    size = m->size;
    for (int i = 0; i < size; i++)
        n.symbols[i] = m->symbols[i];
    n.symbols[size] = val;

    memcpy(m, &n, sizeof(n));

    return 0;
}