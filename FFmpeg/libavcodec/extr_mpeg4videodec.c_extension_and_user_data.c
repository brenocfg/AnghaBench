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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ EXT_STARTCODE ; 
 scalar_t__ QUANT_MATRIX_EXT_ID ; 
 scalar_t__ USER_DATA_STARTCODE ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_quant_matrix_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void extension_and_user_data(MpegEncContext *s, GetBitContext *gb, int id)
{
    uint32_t startcode;
    uint8_t extension_type;

    startcode = show_bits_long(gb, 32);
    if (startcode == USER_DATA_STARTCODE || startcode == EXT_STARTCODE) {

        if ((id == 2 || id == 4) && startcode == EXT_STARTCODE) {
            skip_bits_long(gb, 32);
            extension_type = get_bits(gb, 4);
            if (extension_type == QUANT_MATRIX_EXT_ID)
                read_quant_matrix_ext(s, gb);
        }
    }
}