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
typedef  int /*<<< orphan*/  me_cmp_func ;
typedef  int /*<<< orphan*/  MpegEncContext ;

/* Variables and functions */
 int cmp_inline (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_simple(MpegEncContext *s, const int x, const int y,
                      int ref_index, int src_index,
                      me_cmp_func cmp_func, me_cmp_func chroma_cmp_func){
    return cmp_inline(s,x,y,0,0,0,16,ref_index,src_index, cmp_func, chroma_cmp_func, 0, 0);
}