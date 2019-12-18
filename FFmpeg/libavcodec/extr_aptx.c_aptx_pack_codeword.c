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
typedef  int uint16_t ;
typedef  int int32_t ;
struct TYPE_6__ {TYPE_1__* quantize; } ;
struct TYPE_5__ {int quantized_sample; } ;
typedef  TYPE_2__ Channel ;

/* Variables and functions */
 int aptx_quantized_parity (TYPE_2__*) ; 

__attribute__((used)) static uint16_t aptx_pack_codeword(Channel *channel)
{
    int32_t parity = aptx_quantized_parity(channel);
    return (((channel->quantize[3].quantized_sample & 0x06) | parity) << 13)
         | (((channel->quantize[2].quantized_sample & 0x03)         ) << 11)
         | (((channel->quantize[1].quantized_sample & 0x0F)         ) <<  7)
         | (((channel->quantize[0].quantized_sample & 0x7F)         ) <<  0);
}