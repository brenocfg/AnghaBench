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
struct TYPE_5__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ VC2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_picture_header (TYPE_1__*) ; 
 int /*<<< orphan*/  encode_wavelet_transform (TYPE_1__*) ; 

__attribute__((used)) static void encode_picture_start(VC2EncContext *s)
{
    avpriv_align_put_bits(&s->pb);
    encode_picture_header(s);
    avpriv_align_put_bits(&s->pb);
    encode_wavelet_transform(s);
}