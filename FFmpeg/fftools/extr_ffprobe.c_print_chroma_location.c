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
typedef  enum AVChromaLocation { ____Placeholder_AVChromaLocation } AVChromaLocation ;
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 int AVCHROMA_LOC_UNSPECIFIED ; 
 char* av_chroma_location_name (int) ; 
 int /*<<< orphan*/  print_str (char*,char const*) ; 
 int /*<<< orphan*/  print_str_opt (char*,char*) ; 

__attribute__((used)) static void print_chroma_location(WriterContext *w, enum AVChromaLocation chroma_location)
{
    const char *val = av_chroma_location_name(chroma_location);
    if (!val || chroma_location == AVCHROMA_LOC_UNSPECIFIED) {
        print_str_opt("chroma_location", "unspecified");
    } else {
        print_str("chroma_location", val);
    }
}