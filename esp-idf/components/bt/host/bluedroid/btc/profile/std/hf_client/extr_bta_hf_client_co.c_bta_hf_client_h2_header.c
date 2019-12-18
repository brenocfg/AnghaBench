#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT16 ;
struct TYPE_2__ {int sequence_number; } ;

/* Variables and functions */
 int BTA_HF_H2_HEADER ; 
 int BTA_HF_H2_HEADER_BIT0_MASK ; 
 int BTA_HF_H2_HEADER_BIT1_MASK ; 
 int BTA_HF_H2_HEADER_SN0_BIT_OFFSET1 ; 
 int BTA_HF_H2_HEADER_SN0_BIT_OFFSET2 ; 
 int BTA_HF_H2_HEADER_SN1_BIT_OFFSET1 ; 
 int BTA_HF_H2_HEADER_SN1_BIT_OFFSET2 ; 
 TYPE_1__ bta_hf_client_co_cb ; 

__attribute__((used)) static void bta_hf_client_h2_header(UINT16 *p_buf)
{
    // H2: Header with synchronization word and sequence number
#define BTA_HF_H2_HEADER                0x0801
#define BTA_HF_H2_HEADER_BIT0_MASK   (1 << 0)
#define BTA_HF_H2_HEADER_BIT1_MASK   (1 << 1)
#define BTA_HF_H2_HEADER_SN0_BIT_OFFSET1 12
#define BTA_HF_H2_HEADER_SN0_BIT_OFFSET2 13
#define BTA_HF_H2_HEADER_SN1_BIT_OFFSET1 14
#define BTA_HF_H2_HEADER_SN1_BIT_OFFSET2 15

    UINT16 h2_header = BTA_HF_H2_HEADER;
    UINT8 h2_header_sn0 = bta_hf_client_co_cb.sequence_number & BTA_HF_H2_HEADER_BIT0_MASK;
    UINT8 h2_header_sn1 = bta_hf_client_co_cb.sequence_number & BTA_HF_H2_HEADER_BIT1_MASK;
    h2_header |= (h2_header_sn0 << BTA_HF_H2_HEADER_SN0_BIT_OFFSET1
                | h2_header_sn0 << BTA_HF_H2_HEADER_SN0_BIT_OFFSET2
                | h2_header_sn1 << (BTA_HF_H2_HEADER_SN1_BIT_OFFSET1 - 1)
                | h2_header_sn1 << (BTA_HF_H2_HEADER_SN1_BIT_OFFSET2 - 1)
                );

    bta_hf_client_co_cb.sequence_number++;
    *p_buf = h2_header;
}