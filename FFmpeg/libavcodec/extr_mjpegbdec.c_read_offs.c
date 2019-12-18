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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t read_offs(AVCodecContext *avctx, GetBitContext *gb, uint32_t size, const char *err_msg){
    uint32_t offs= get_bits_long(gb, 32);
    if(offs >= size){
        av_log(avctx, AV_LOG_WARNING, err_msg, offs, size);
        return 0;
    }
    return offs;
}