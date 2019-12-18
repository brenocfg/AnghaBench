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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkImage ;
typedef  int /*<<< orphan*/  GtkIconSize ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_image_set_from_icon_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ghb_image_set_from_icon_name(GtkImage * image, const gchar * name,
                             GtkIconSize size)
{
    gtk_image_set_from_icon_name(image, name, size);
}