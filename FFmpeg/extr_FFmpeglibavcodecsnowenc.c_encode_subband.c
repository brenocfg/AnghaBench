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
typedef  int /*<<< orphan*/  SubBand ;
typedef  int /*<<< orphan*/  SnowContext ;
typedef  int /*<<< orphan*/  IDWTELEM ;

/* Variables and functions */
 int encode_subband_c0run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int encode_subband(SnowContext *s, SubBand *b, const IDWTELEM *src, const IDWTELEM *parent, int stride, int orientation){
//    encode_subband_qtree(s, b, src, parent, stride, orientation);
//    encode_subband_z0run(s, b, src, parent, stride, orientation);
    return encode_subband_c0run(s, b, src, parent, stride, orientation);
//    encode_subband_dzr(s, b, src, parent, stride, orientation);
}