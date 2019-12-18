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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int COUNT ; 
 int EXTEND (int) ; 
 int EXTEND_L (int) ; 
 int SIZE ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int get_se_golomb (int /*<<< orphan*/ *) ; 
 int get_ue_golomb (int /*<<< orphan*/ *) ; 
 int get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_se_golomb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_ue_golomb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_ue_golomb_long (int /*<<< orphan*/ *,int) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
    int i, ret = 0;
    uint8_t *temp;
    PutBitContext pb;
    GetBitContext gb;

    temp = av_malloc(SIZE);
    if (!temp)
        return 2;

    init_put_bits(&pb, temp, SIZE);
    for (i = 0; i < COUNT; i++)
        set_ue_golomb(&pb, i);
    flush_put_bits(&pb);

    init_get_bits(&gb, temp, 8 * SIZE);
    for (i = 0; i < COUNT; i++) {
        int j, s = show_bits(&gb, 25);

        j = get_ue_golomb(&gb);
        if (j != i) {
            fprintf(stderr, "get_ue_golomb: expected %d, got %d. bits: %7x\n",
                    i, j, s);
            ret = 1;
        }
    }

#define EXTEND(i) ((i) << 3 | (i) & 7)
    init_put_bits(&pb, temp, SIZE);
    for (i = 0; i < COUNT; i++)
        set_ue_golomb(&pb, EXTEND(i));
    flush_put_bits(&pb);

    init_get_bits(&gb, temp, 8 * SIZE);
    for (i = 0; i < COUNT; i++) {
        int j, s = show_bits_long(&gb, 32);

        j = get_ue_golomb_long(&gb);
        if (j != EXTEND(i)) {
            fprintf(stderr, "get_ue_golomb_long: expected %d, got %d. "
                    "bits: %8x\n", EXTEND(i), j, s);
            ret = 1;
        }
    }

#define EXTEND_L(i) ((i) << 4 | (i) & 15)
    init_put_bits(&pb, temp, SIZE);
    for (i = 0; i < COUNT; i++)
        set_ue_golomb_long(&pb, EXTEND_L(i));
    flush_put_bits(&pb);

    init_get_bits(&gb, temp, 8 * SIZE);
    for (i = 0; i < COUNT; i++) {
        int j, s = show_bits_long(&gb, 32);

        j = get_ue_golomb_long(&gb);
        if (j != EXTEND_L(i)) {
            fprintf(stderr, "get_ue_golomb_long: expected %d, got %d. "
                    "bits: %8x\n", EXTEND_L(i), j, s);
            ret = 1;
        }
    }

    init_put_bits(&pb, temp, SIZE);
    for (i = 0; i < COUNT; i++)
        set_se_golomb(&pb, i - COUNT / 2);
    flush_put_bits(&pb);

    init_get_bits(&gb, temp, 8 * SIZE);
    for (i = 0; i < COUNT; i++) {
        int j, s = show_bits(&gb, 25);

        j = get_se_golomb(&gb);
        if (j != i - COUNT / 2) {
            fprintf(stderr, "get_se_golomb: expected %d, got %d. bits: %7x\n",
                    i - COUNT / 2, j, s);
            ret = 1;
        }
    }

    av_free(temp);

    return ret;
}