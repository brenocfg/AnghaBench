#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int width; int height; struct TYPE_7__* data; } ;
typedef  TYPE_1__ gx_texture ;
struct TYPE_8__ {int /*<<< orphan*/  keys; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int ASND_GetFirstUnusedVoice () ; 
 int /*<<< orphan*/  ASND_Pause (int) ; 
 int /*<<< orphan*/  ASND_SetVoice (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BLACK ; 
 int /*<<< orphan*/  Bg_intro_c1_png ; 
 int /*<<< orphan*/  Bg_intro_c2_png ; 
 int /*<<< orphan*/  Bg_intro_c3_png ; 
 int /*<<< orphan*/  Bg_intro_c4_png ; 
 int /*<<< orphan*/  FONT_writeCenter (char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUI_FadeOut () ; 
 int /*<<< orphan*/  Key_A_gcn_png ; 
 int /*<<< orphan*/  Key_A_wii_png ; 
 scalar_t__ SKY_BLUE ; 
 int /*<<< orphan*/  VOICE_MONO_16BIT ; 
 scalar_t__ WHITE ; 
 scalar_t__ button_select_pcm ; 
 int /*<<< orphan*/  button_select_pcm_size ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gxClearScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxDrawTexture (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 int /*<<< orphan*/  gxTextureClose (TYPE_1__**) ; 
 TYPE_1__* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intro_pcm ; 
 int /*<<< orphan*/  intro_pcm_size ; 
 TYPE_2__ m_input ; 
 int /*<<< orphan*/  show_disclaimer (int) ; 
 int /*<<< orphan*/  sleep (int) ; 

void legal ()
{
  int count = 2000;
  int vis = 0;

#ifdef HW_RVL
  gx_texture *button = gxTextureOpenPNG(Key_A_wii_png,0);
#else
  gx_texture *button = gxTextureOpenPNG(Key_A_gcn_png,0);
#endif
  gx_texture *logo = gxTextureOpenPNG(Bg_intro_c4_png,0);

  gxClearScreen((GXColor)BLACK);
  show_disclaimer(56);
  gxDrawTexture(logo, (640-logo->width)/2, 480-24-logo->height, logo->width, logo->height,255);
  gxSetScreen();
  sleep(1);

  while (!m_input.keys && count)
  {
    gxClearScreen((GXColor)BLACK);
    show_disclaimer(56);
    if (count%25 == 0) vis^=1;
    if (vis)
    {
      FONT_writeCenter("Press    button to continue.",24,0,640,366,(GXColor)SKY_BLUE);
      gxDrawTexture(button, 220, 366-24+(24-button->height)/2,  button->width, button->height,255);
    }
    gxDrawTexture(logo, (640-logo->width)/2, 480-24-logo->height, logo->width, logo->height,255);
    gxSetScreen();
    count--;
  }

  gxTextureClose(&button);
  gxTextureClose(&logo);

  if (count > 0)
  {
    ASND_Pause(0);
    int voice = ASND_GetFirstUnusedVoice();
    ASND_SetVoice(voice,VOICE_MONO_16BIT,44100,0,(u8 *)button_select_pcm,button_select_pcm_size,200,200,NULL);
    GUI_FadeOut();
    ASND_Pause(1);
    return;
  }

  gxClearScreen((GXColor)BLACK);
  gx_texture *texture = gxTextureOpenPNG(Bg_intro_c1_png,0);
  if (texture)
  {
    gxDrawTexture(texture, (640-texture->width)/2, (480-texture->height)/2,  texture->width, texture->height,255);
    if (texture->data) free(texture->data);
    free(texture);
  }
  gxSetScreen();

  sleep (1);

  gxClearScreen((GXColor)WHITE);
  texture = gxTextureOpenPNG(Bg_intro_c2_png,0);
  if (texture)
  {
    gxDrawTexture(texture, (640-texture->width)/2, (480-texture->height)/2,  texture->width, texture->height,255);
    if (texture->data) free(texture->data);
    free(texture);
  }
  gxSetScreen();

  sleep (1);

  gxClearScreen((GXColor)BLACK);
  texture = gxTextureOpenPNG(Bg_intro_c3_png,0);
  if (texture)
  {
    gxDrawTexture(texture, (640-texture->width)/2, (480-texture->height)/2,  texture->width, texture->height,255);
    if (texture->data) free(texture->data);
    free(texture);
  }
  gxSetScreen();

  ASND_Pause(0);
  int voice = ASND_GetFirstUnusedVoice();
  ASND_SetVoice(voice,VOICE_MONO_16BIT,44100,0,(u8 *)intro_pcm,intro_pcm_size,200,200,NULL);
  sleep (2);
  ASND_Pause(1);
}