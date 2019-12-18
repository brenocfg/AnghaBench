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

/* Variables and functions */
 float av_clipf (float const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static float get_component(float v, float l,
                           float s, float m, float h)
{
    const float a = 4.f, b = 0.333f, scale = 0.7f;

    s *= av_clipf((b - l) * a + 0.5f, 0, 1) * scale;
    m *= av_clipf((l - b) * a + 0.5f, 0, 1) * av_clipf((1.0 - l - b) * a + 0.5f, 0, 1) * scale;
    h *= av_clipf((l + b - 1) * a + 0.5f, 0, 1) * scale;

    v += s;
    v += m;
    v += h;

    return av_clipf(v, 0, 1);
}