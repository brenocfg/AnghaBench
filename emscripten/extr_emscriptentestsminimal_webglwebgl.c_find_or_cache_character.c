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
struct TYPE_4__ {unsigned int ch; int charSize; int shadow; int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ Glyph ;

/* Variables and functions */
 int MAX_TEXTURES ; 
 int /*<<< orphan*/  create_texture () ; 
 TYPE_1__* glyphs ; 
 int /*<<< orphan*/  upload_unicode_char_to_texture (unsigned int,int,int) ; 

__attribute__((used)) static Glyph *find_or_cache_character(unsigned int ch, int charSize, int shadow)
{
  for(int i = 0; i < MAX_TEXTURES; ++i) // Naive O(n) lookup for tiny code size
    if (glyphs[i].ch == ch && glyphs[i].charSize == charSize && glyphs[i].shadow == shadow)
      return glyphs+i;
    else if (!glyphs[i].ch)
    {
      glyphs[i].ch = ch;
      glyphs[i].charSize = charSize;
      glyphs[i].shadow = shadow;
      glyphs[i].texture = create_texture();
      upload_unicode_char_to_texture(ch, charSize, shadow);
      return glyphs+i;
    }
  return 0; // fail
}