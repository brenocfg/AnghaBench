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
struct microdvd_tag {char key; int data1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICRODVD_TAGS ; 
 size_t indexof (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  microdvd_set_tag (struct microdvd_tag*,struct microdvd_tag) ; 

__attribute__((used)) static char *check_for_italic_slash_marker(struct microdvd_tag *tags, char *s)
{
    if (*s == '/') {
        struct microdvd_tag tag = tags[indexof(MICRODVD_TAGS, 'y')];
        tag.key = 'y';
        tag.data1 |= 1 << 0 /* 'i' position in MICRODVD_STYLES */;
        microdvd_set_tag(tags, tag);
        s++;
    }
    return s;
}