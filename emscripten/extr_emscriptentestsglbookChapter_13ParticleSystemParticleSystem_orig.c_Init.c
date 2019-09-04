#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float* particleData; float time; scalar_t__ textureId; int /*<<< orphan*/  programObject; void* samplerLoc; void* colorLoc; void* centerPositionLoc; void* timeLoc; void* endPositionLoc; void* startPositionLoc; void* lifetimeLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {TYPE_1__* userData; } ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ LoadTexture (char*) ; 
 int NUM_PARTICLES ; 
 int PARTICLE_SIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 void* glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 double myrandom () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

int Init ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   int i;
   
   GLbyte vShaderStr[] =
      "uniform float u_time;		                           \n"
      "uniform vec3 u_centerPosition;                       \n"
      "attribute float a_lifetime;                          \n"
      "attribute vec3 a_startPosition;                      \n"
      "attribute vec3 a_endPosition;                        \n"
      "varying float v_lifetime;                            \n"
      "void main()                                          \n"
      "{                                                    \n"
      "  if ( u_time <= a_lifetime )                        \n"
      "  {                                                  \n"
      "    gl_Position.xyz = a_startPosition +              \n"
      "                      (u_time * a_endPosition);      \n"
      "    gl_Position.xyz += u_centerPosition;             \n"
      "    gl_Position.w = 1.0;                             \n"
      "  }                                                  \n"
      "  else                                               \n"
      "     gl_Position = vec4( -1000, -1000, 0, 0 );       \n"
      "  v_lifetime = 1.0 - ( u_time / a_lifetime );        \n"
      "  v_lifetime = clamp ( v_lifetime, 0.0, 1.0 );       \n"
      "  gl_PointSize = ( v_lifetime * v_lifetime ) * 40.0; \n"
      "}";
      
   GLbyte fShaderStr[] =  
      "precision mediump float;                             \n"
      "uniform vec4 u_color;		                           \n"
      "varying float v_lifetime;                            \n"
      "uniform sampler2D s_texture;                         \n"
      "void main()                                          \n"
      "{                                                    \n"
      "  vec4 texColor;                                     \n"
      "  texColor = texture2D( s_texture, gl_PointCoord );  \n"
      "  gl_FragColor = vec4( u_color ) * texColor;         \n"
      "  gl_FragColor.a *= v_lifetime;                      \n"
      "}                                                    \n";

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->lifetimeLoc = glGetAttribLocation ( userData->programObject, "a_lifetime" );
   userData->startPositionLoc = glGetAttribLocation ( userData->programObject, "a_startPosition" );
   userData->endPositionLoc = glGetAttribLocation ( userData->programObject, "a_endPosition" );
   
   // Get the uniform locations
   userData->timeLoc = glGetUniformLocation ( userData->programObject, "u_time" );
   userData->centerPositionLoc = glGetUniformLocation ( userData->programObject, "u_centerPosition" );
   userData->colorLoc = glGetUniformLocation ( userData->programObject, "u_color" );
   userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

   // Fill in particle data array
   srand ( 0 );
   for ( i = 0; i < NUM_PARTICLES; i++ )
   {
      float *particleData = &userData->particleData[i * PARTICLE_SIZE];
   
      // Lifetime of particle
      (*particleData++) = myrandom();

      // End position of particle
      (*particleData++) = myrandom() * 2 - 1.0f;
      (*particleData++) = myrandom() * 2 - 1.0f;
      (*particleData++) = myrandom() * 2 - 1.0f;

      // Start position of particle
      (*particleData++) = myrandom() * 0.25 - 0.125f;
      (*particleData++) = myrandom() * 0.25 - 0.125f;
      (*particleData++) = myrandom() * 0.25 - 0.125f;

   }

   // Initialize time to cause reset on first update
   userData->time = 1.0f;

   userData->textureId = LoadTexture ( "smoke.tga" );
   if ( userData->textureId <= 0 )
   {
      return FALSE;
   }
   
   return TRUE;
}