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
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avcodec_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_v1_encoder ; 
 int /*<<< orphan*/  dummy_v2_encoder ; 
 int /*<<< orphan*/  dummy_v3_encoder ; 
 int /*<<< orphan*/  dummy_v4_encoder ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(void)
{
    AVCodec *dummy_codec[] = {
        &dummy_v1_encoder,
        &dummy_v2_encoder,
        &dummy_v3_encoder,
        &dummy_v4_encoder,
        NULL,
    };
    int i, j;

    for (i = 0; dummy_codec[i]; i++)
        avcodec_register(dummy_codec[i]);

    printf("testing avcodec_copy_context()\n");
    for (i = 0; i < FF_ARRAY_ELEMS(dummy_codec); i++)
        for (j = 0; j < FF_ARRAY_ELEMS(dummy_codec); j++)
            test_copy(dummy_codec[i], dummy_codec[j]);
    return 0;
}