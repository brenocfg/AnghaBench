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
struct TYPE_4__ {struct TYPE_4__* TexBase; int /*<<< orphan*/  Texture; } ;
typedef  TYPE_1__ GSFONTM ;

/* Variables and functions */
 int /*<<< orphan*/  deinit_texture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void deinit_gsfont(GSFONTM *gsFontM)
{
   deinit_texture(gsFontM->Texture);
   free(gsFontM->TexBase);
   gsFontM->TexBase = NULL;
   free(gsFontM);
}