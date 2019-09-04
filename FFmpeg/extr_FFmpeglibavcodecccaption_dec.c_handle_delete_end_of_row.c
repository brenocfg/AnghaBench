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
struct Screen {int dummy; } ;
typedef  int /*<<< orphan*/  CCaptionSubContext ;

/* Variables and functions */
 struct Screen* get_writing_screen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_char (int /*<<< orphan*/ *,struct Screen*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_delete_end_of_row(CCaptionSubContext *ctx, char hi, char lo)
{
    struct Screen *screen = get_writing_screen(ctx);
    write_char(ctx, screen, 0);
}