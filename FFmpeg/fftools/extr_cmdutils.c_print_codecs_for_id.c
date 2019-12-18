#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_4__ {char* name; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 TYPE_1__* next_codec_for_id (int,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_codecs_for_id(enum AVCodecID id, int encoder)
{
    const AVCodec *codec = NULL;

    printf(" (%s: ", encoder ? "encoders" : "decoders");

    while ((codec = next_codec_for_id(id, codec, encoder)))
        printf("%s ", codec->name);

    printf(")");
}