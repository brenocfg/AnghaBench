#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* s; } ;
typedef  TYPE_2__ stbi__jpeg ;
struct TYPE_5__ {int /*<<< orphan*/  img_n; } ;

/* Variables and functions */
 int /*<<< orphan*/  stbi__free_jpeg_components (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stbi__cleanup_jpeg(stbi__jpeg *j)
{
   stbi__free_jpeg_components(j, j->s->img_n, 0);
}