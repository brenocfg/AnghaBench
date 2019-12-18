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
 int const FLAG_CHROMA ; 
 int const FLAG_DIRECT ; 
 int const FLAG_QPEL ; 
 int cmp_direct_inline (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int cmp_inline (int /*<<< orphan*/ *,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int cmp_fpel_internal(MpegEncContext *s, const int x, const int y,
                      const int size, const int h, int ref_index, int src_index,
                      me_cmp_func cmp_func, me_cmp_func chroma_cmp_func, const int flags){
    if(flags&FLAG_DIRECT){
        return cmp_direct_inline(s,x,y,0,0,size,h,ref_index,src_index, cmp_func, chroma_cmp_func, flags&FLAG_QPEL);
    }else{
        return cmp_inline(s,x,y,0,0,size,h,ref_index,src_index, cmp_func, chroma_cmp_func, 0, flags&FLAG_CHROMA);
    }
}